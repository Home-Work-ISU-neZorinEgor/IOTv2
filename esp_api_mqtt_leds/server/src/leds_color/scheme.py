from pydantic import BaseModel


class PixelsColors(BaseModel):
    colors: str
