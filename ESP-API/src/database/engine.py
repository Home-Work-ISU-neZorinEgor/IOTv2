from sqlalchemy import create_engine
from src.database.config import settings

engine = create_engine(
    url=settings.mysql_url(),
    echo=False
)
