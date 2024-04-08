from fastapi import APIRouter, Depends
from fastapi.responses import JSONResponse

from src.auth.scheme import FullUserInfo
from src.auth.router import check_auth
from src.database import SqliteDB
from src.leds_color.scheme import PixelsColors

colors_router = APIRouter(prefix='/colors', tags=['PixelsColors'])


@colors_router.post('/create')
def set_colors(pixel: PixelsColors, auth: FullUserInfo = Depends(check_auth)):
    engine = SqliteDB()
    stmt = f"""
        INSERT INTO Colors (color_series, user_id) VALUES ('{pixel.colors}', '{auth.id}')
    """
    engine.execute_query(stmt)
    engine.close_connection()
    return JSONResponse({'ok': True, 'message': "Save colors successful"})


@colors_router.get('/my-series')
def get_user_colors_list(auth: FullUserInfo = Depends(check_auth)):
    engine = SqliteDB()
    unbox_list = list()
    stmt = f"""
        SELECT color_series FROM Colors;
    """
    debug = engine.execute_query(stmt)
    engine.close_connection()
    print(debug)
    for i in debug:
        unbox_list.append(*i)
    return unbox_list


