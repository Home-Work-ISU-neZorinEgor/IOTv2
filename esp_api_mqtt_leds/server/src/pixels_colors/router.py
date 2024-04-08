import random

from fastapi import APIRouter, Depends
from fastapi.responses import JSONResponse

from src.auth.scheme import FullUserInfo
from src.auth.router import check_auth
from src.database import SqliteDB
from src.pixels_colors.scheme import PixelsColors

colors_router = APIRouter(prefix='/colors', tags=['PixelsColors'])


@colors_router.post('/create')
def save_colors(pixel: PixelsColors, auth: FullUserInfo = Depends(check_auth)):
    """ The handler stores the color combination for a specific user """
    engine = SqliteDB()
    stmt = f"""
        INSERT INTO Colors (color_series, user_id) VALUES ('{pixel.colors}', '{auth.id}')
    """
    engine.execute_query(stmt)
    engine.close_connection()
    return JSONResponse({'ok': True, 'message': "Save colors successful"})


@colors_router.get('/my-colors')
def get_user_colors_list(auth: FullUserInfo = Depends(check_auth)):
    """ The handler return combinations of colors for specific user or reports that there are none."""
    engine = SqliteDB()
    unbox_list = list()
    stmt = f"""
        SELECT color_series FROM Colors WHERE user_id='{auth.id}';
    """
    debug = engine.execute_query(stmt)
    engine.close_connection()
    for i in debug:
        unbox_list.append(*i)
    if len(unbox_list) == 0:
        return "Not one color combination found"
    return unbox_list


@colors_router.get('/generate')
def generate_color_combination():
    pixel_count = random.randint(1, 10)
    combo = ""
    color = random.randint(1, 3)
    value = random.randint(0, 255)

    if len(str(value)) == 2: value = "0" + str(value)
    if len(str(value)) == 1: value = "00" + str(value)

    series = 255 - int(value) / pixel_count
    for i in range(pixel_count):
        pass   # TODO: finish algo

    match color:
        case 1:
            combo = str(value) + "000000"  # red
        case 2:
            combo = "000" + str(value) + "000"  # green
        case 3:
            combo = "000000" + str(value)  # blue

    return combo
