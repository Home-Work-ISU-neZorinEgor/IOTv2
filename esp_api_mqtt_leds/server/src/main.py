from fastapi import FastAPI
import uvicorn

app = FastAPI(title='leds')


uvicorn.run(app, host='172.18.59.144', port=5000)
