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

class CurrencyMixin:
    known_currencies = set(['EUR','USD','CHF'])
    currency  = Column(String(3))
        
    @validates('currency')
    def validate_currency(self,key,currency):
        currency = currency.upper()
        assert currency in CurrencyMixin.known_currencies
        return currency
            
class User(Base):
    __tablename__ = 'users'

    id = Column(Integer, primary_key=True)
    first_name = Column(String(25))
    last_name = Column(String(25))
    birthday = Column(Date())
    
    @required_keywords('first_name','last_name','birthday')
    def __init__(self,**kwargs):
        pass

    def __repr__(self):
        return "<User(ID=%s, name='%s %s', birthday=%s)>" % (str(self.id), self.first_name, self.last_name,str(self.birthday))

class Depot(Base,CurrencyMixin):
    __tablename__ = 'depots'

    id        = Column(Integer, primary_key=True)
    account   = Column(String(19))
    institute = Column(String(50))
    user_id   = Column(Integer, ForeignKey('users.id'))
    
    user = relationship("User", back_populates="depots")
    
    @keywords_with_defaults(currency="EUR")
    @required_keywords('account','institute')
    def __init__(self,**kwargs):
        pass
        
    def __repr__(self):
        return "<Depot(ID=%r, account=%s, institute='%s', currency=%s, user='%r')>" % \
                (self.id, self.account, self.institute, self.currency, self.user)
 
    @validates('account')
    def validate_account(self,key,account):
        account_format = re.compile("\d{4}-\d{4}-\d{4}-\d{4}")
        assert account_format.match(account)
        return account

User.depots = relationship("Depot", back_populates="user")

class Asset(Base,CurrencyMixin):
    __tablename__ = "assets"
    
    symbol = Column(String(10),primary_key=True)
    sector = Column(String(100))
    region = Column(String(100))
    type   = Column(String(20))
    
    @keywords_with_defaults(currency="EUR",sector="other",region="other")
    @required_keywords('symbol','type')
    def __init__(self,**kwargs):
        pass

    def __repr__(self):
        return "<Asset(symbol='%s', type=%s, currency=%s, sector=%s, region=%s)>" % \
                (self.symbol, self.type, self.currency, self.sector, self.region)
