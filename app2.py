from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from ORM import User, Depot, Asset

engine = create_engine('sqlite:///test.db')

Session = sessionmaker(bind=engine)
session = Session()

for user in session.query(User).order_by(User.id):
    print user
    
for depot in session.query(Depot).order_by(Depot.id):
    print depot
    
for asset in session.query(Asset).order_by(Asset.symbol):
    print asset    