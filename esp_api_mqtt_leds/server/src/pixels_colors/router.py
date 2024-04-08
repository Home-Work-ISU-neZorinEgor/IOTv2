import random
from fastapi import APIRouter, Depends
from fastapi.responses import JSONResponse

from src.auth.scheme import FullUserInfo
from src.auth.router import check_auth
from src.database import SqliteDB
from src.pixels_colors.scheme import PixelsColors

colors_router = APIRouter(prefix='/colors', tags=['PixelsColors'])


@colors_router.post('/save')
def save_colors(pixel: PixelsColors, auth: FullUserInfo = Depends(check_auth)):
    """ The handler stores the color combination for a specific user """
    engine = SqliteDB()
    stmt = f"""
        INSERT INTO Colors (color_series, user_id) VALUES ('{pixel.colors}', '{auth.id}')
    """
    engine.execute_query(stmt)
    engine.close_connection()
    return JSONResponse({'ok': True, 'message': "Save colors successful"})


@colors_router.get('/get-my-colors')
def get_user_colors_list(auth: FullUserInfo = Depends(check_auth)) -> str | list[str]:
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
def generate_color_combination(pixel_count: int, auth: FullUserInfo = Depends(check_auth)) -> str:
    """ Algorithm for creating a smoothly transitioning shade """
    colors = list()
    pixel_color = random.randint(1, 3)
    value = random.randint(0, 120)
    if len(str(value)) == 2: value = "0" + str(value)
    if len(str(value)) == 1: value = "00" + str(value)
    series = (255 - int(value)) // pixel_count
    value = int(value)
    for i in range(pixel_count):
        value += series
        if pixel_color == 1: colors.append(str(value) + "000000")   # red
        if pixel_color == 2: colors.append("000" + str(value) + "000")   # green
        if pixel_color == 3: colors.append("000000" + str(value))    # blue
    return ''.join(colors)
