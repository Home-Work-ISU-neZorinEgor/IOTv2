from pydantic import BaseModel


class PostTemperature(BaseModel):
    value: float
    location: str | None


class GetTemperature(BaseModel):
    id: int
    value: float
    location: str | None
