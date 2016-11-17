from sqlalchemy import Column, Integer, String, event, ForeignKey, Date
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class User(Base):
    __tablename__ = 'users'

    id = Column(Integer, primary_key=True)
    first_name = Column(String(25))
    last_name = Column(String(25))
    birthday = Date()
    
    def __repr__(self):
        return "<User(ID=%s, name='%s %s', birthday=%s)>" % (str(self.id), self.first_name, self.last_name,str(self.birthday))

class Depot(Base):
    __tablename__ = 'depots'

    id        = Column(Integer, primary_key=True)
    institute = Column(String(50))
    user_id   = Column(Integer, ForeignKey('users.id'))
    
    user = relationship("User", back_populates="depots")
    
    def __repr__(self):
        return "<Depot(ID=%s, institute='%s', User='%s')>" % (str(self.id), self.institute,str(self.user))
 
User.depots = relationship("Depot", back_populates="user")
        
@event.listens_for(User.depots,'append')
def my_listener(target,value,initiator):
    print target
    print value
    print initiator