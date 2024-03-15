from fastapi import FastAPI
from src.device.router import create_tables, temperature_router
import uvicorn


def main():
    create_tables()  # drop and create db: For test
    app = FastAPI()
    app.include_router(temperature_router)
    uvicorn.run(app, host='192.168.0.184', port=5000)


if __name__ == '__main__':
    main()


