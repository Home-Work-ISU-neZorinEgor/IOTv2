from fastapi import FastAPI
import uvicorn

from server.src.auth.route import auth_router

app = FastAPI(title='leds')
app.include_router(auth_router)

uvicorn.run(app, host='172.20.10.10', port=5000)
