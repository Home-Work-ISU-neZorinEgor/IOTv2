from pydantic import BaseModel


class UserResponse(BaseModel):
    username: str
    password: str


class FullUserInfo(UserResponse):
    id: int
