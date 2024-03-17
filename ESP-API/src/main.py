from fastapi import FastAPI
from src.device.router import create_temperature_table, temperature_router
import uvicorn

create_temperature_table()

app = FastAPI(title='Device api', version='1.0')
app.include_router(temperature_router)
uvicorn.run(app, host='127.0.0.1', port=5000, reload=False)

