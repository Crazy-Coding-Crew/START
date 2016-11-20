from sqlalchemy import Column, Integer, String, event, ForeignKey, Date
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm.mapper import validates
import re

Base = declarative_base()

def keywords_with_defaults(**default_values):
    assert isinstance(default_values, dict)
    def decorator_generator(func):
        def func_wrapper(self,**kwargs):
            default_args = set(default_values.keys()) - set(kwargs.keys())
            cls_ = type(self)
            for k in default_args:
                if not hasattr(cls_, k):
                    raise TypeError("%r is an invalid default keyword for %s" % (k, cls_.__name__))
                setattr(self, k, default_values[k])            
            func(self,**kwargs)
        return func_wrapper
    return decorator_generator

def required_keywords(*keywords):
    keywords = set(keywords)
    def decorator_generator(func):
        def func_wrapper(self,**kwargs):
            cls_ = type(self)
            missing_args = keywords - set(kwargs.keys())
            if missing_args:
                raise TypeError("missing the following required keyword argument(s) for %s: %r" % (cls_.__name__, list(missing_args)))
            for k in kwargs:
                if not hasattr(cls_, k):
                    raise TypeError("%r is an invalid keyword argument for %s" % (k, cls_.__name__))
                setattr(self, k, kwargs[k])            
            func(self,**kwargs)
        return func_wrapper
    return decorator_generator

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
    account   = Column(String(19))
    institute = Column(String(50))
    currency  = Column(String(3))
    user_id   = Column(Integer, ForeignKey('users.id'))
    
    user = relationship("User", back_populates="depots")
    
    @keywords_with_defaults(currency="EUR")
    @required_keywords('account','institute')
    def __init__(self,**kwargs):
        pass
        
    @validates('account')
    def validate_account(self,key,account):
        account_format = re.compile("\d{4}-\d{4}-\d{4}-\d{4}")
        assert account_format.match(account)
        return account

    @validates('currencies')
    def validate_currency(self,key,currency):
        known_currencies = set(['EUR','USD','CHF'])
        assert currency in known_currencies
        return currency
            
    def __repr__(self):
        return "<Depot(ID=%r, account=%s, institute='%s', currency=%s, user='%r')>" % \
                (self.id, self.account, self.institute, self.currency, self.user)
 
User.depots = relationship("Depot", back_populates="user")
