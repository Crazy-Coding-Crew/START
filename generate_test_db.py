import os
from datetime import date
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from ORM import Base, User, Depot, Asset

def generate_test_db(db_file = "test.db"):
    if os.path.isfile(db_file):
        os.remove(db_file)
    engine = create_engine('sqlite:///%s' % db_file, echo=False)
    Base.metadata.create_all(engine)

    Session = sessionmaker(bind=engine)
    session = Session()

    Jack = User(first_name="Jack", last_name="Ripper", birthday=date(1981,9,13))
    Jack.depots.append(Depot(account="1234-4567-2312-0200",institute="DAB"))
    Jack.depots.append(Depot(institute="UBS",account="8123-9323-2290-3884"))
    session.add(Jack)
    
    Bibbi = User(first_name="Bibbi", last_name="Blocksberg", birthday=date(1992,2,29))
    Bibbi.depots.append(Depot(institute="DAB",account="0000-5000-2311-9827"))
    Bibbi.depots.append(Depot(institute="UBS",account="9123-7341-9552-0199"))
    session.add(Bibbi)
    
    google = Asset(symbol="GOOGL",type="stock",sector="technology")
    session.add(google)
    
    session.commit()

generate_test_db()