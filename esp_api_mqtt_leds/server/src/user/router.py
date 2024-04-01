from fastapi import APIRouter
from server.src.database import engine
from sqlalchemy import text

from server.src.user.scheme import User

user_router = APIRouter()


@user_router.post('/register')
def register_user(user: User):
    with engine.connect() as conn:
        stmt = text("INSERT INTO `users` (username, password) VALUES (:username, :password)")
        conn.execute(stmt, {'username': user.username, 'password': user.password})
        conn.commit()
