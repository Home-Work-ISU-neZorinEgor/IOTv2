from fastapi import APIRouter, status, Depends
from fastapi.security import HTTPBasic, HTTPBasicCredentials
from fastapi.responses import JSONResponse

from src.auth.exceptions import unauthorized_exception, exists_suer
from src.database import SqliteDB
from src.auth.scheme import User

from typing import Annotated

auth_router = APIRouter(prefix="/auth")
security = HTTPBasic()


def check_auth(credentials: Annotated[HTTPBasicCredentials, Depends(security)]) -> User:
    engine = SqliteDB()
    try:
        user = engine.execute_query(f"""
            SELECT * FROM Users WHERE username='{credentials.username}' AND password='{credentials.password}'
                    """)
        if user:
            return User(username=user[0][0], password=user[0][1])
        else:
            raise unauthorized_exception
    finally:
        engine.close_connection()


@auth_router.get("/check/whoami", response_model=User)
def whoami(auth: User = Depends(check_auth)):
    return {"name": auth.username, "password": auth.password}


@auth_router.post("/register")
def register(user: User):
    engine = SqliteDB()
    try:
        exist_user = engine.execute_query(f"SELECT * FROM Users WHERE username='{user.username}'")
        if exist_user:
            raise exists_suer
        else:
            stmt = "INSERT INTO Users(username, password) VALUES (?, ?)"
            args = [(user.username, user.password)]
            engine.execute_query(stmt, args)
            return JSONResponse(
                {
                    "ok": True,
                    "detail": f"Register user {user.username} successfully."
                })
    finally:
        engine.close_connection()
