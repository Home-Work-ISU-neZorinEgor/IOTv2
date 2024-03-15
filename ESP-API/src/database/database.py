from sqlalchemy import create_engine
from src.database.config import settings

engine = create_engine(
    url=settings.DATABASE_URL_MYSQL(),
    echo=False,
    pool_size=5,
    max_overflow=10,
)



