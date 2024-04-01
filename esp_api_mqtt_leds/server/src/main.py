from fastapi import FastAPI
import uvicorn

from server.src.auth.route import auth_router
from server.src.user.router import user_router
from server.src.user.model import create_user_table

app = FastAPI(title='leds')

create_user_table()

app.include_router(auth_router)
app.include_router(user_router)

uvicorn.run(app, host='172.18.59.144', port=5000)
