from fastapi import FastAPI
import uvicorn

from src.database import engin
from src.auth.model import create_user_table
from src.auth.router import auth_router

create_user_table(engin)

app = FastAPI(title='leds')
app.include_router(auth_router)


uvicorn.run(app, host='0.0.0.0', port=5000)
