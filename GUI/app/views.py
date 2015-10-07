from flask import render_template,Response,request
import json
from app import app
import Start

@app.route('/')
@app.route('/index')
def index():
        return render_template('base.html')

@app.route('/update')
def update():
        ISIN = request.args.get("ISIN","",type=str)
        if not ISIN:
                print "Error"
        r = {'data' :Start.getShare(ISIN),'name': ISIN}
        result = Response(json.dumps(r),mimetype='application/json')
        return result

@app.route('/shares')
def getListOfShares():
        r = Start.getListOfISINs()
        result = Response(json.dumps(r),mimetype='application/json')
        return result
