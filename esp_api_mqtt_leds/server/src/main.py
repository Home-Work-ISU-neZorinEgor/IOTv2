from fastapi import FastAPI
import uvicorn

from src.database import SqliteDB
from src.auth.model import create_user_table
from src.auth.router import auth_router
from src.pixels.model import create_color_leds_table
from src.pixels.router import pixel_router


def create_tables():
    engine = SqliteDB()
    create_user_table(engine)
    create_color_leds_table(engine)
    engine.close_connection()

create_tables()
app = FastAPI(title='leds')

app.include_router(auth_router)
app.include_router(pixel_router)

uvicorn.run(app, host='127.0.0.1', port=5000)
