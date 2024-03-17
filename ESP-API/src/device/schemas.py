from pydantic import BaseModel
from typing import List


class GetTemperature(BaseModel):
    values: List[float]
    location: str
    
    
class PostTemperatureResponse(BaseModel):
    value: float
    location: str


