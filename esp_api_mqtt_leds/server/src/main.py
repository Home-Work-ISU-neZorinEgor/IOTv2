from fastapi import FastAPI
import uvicorn

app = FastAPI(title='leds')

uvicorn.run(app, host='0.0.0.0', port=5000)
