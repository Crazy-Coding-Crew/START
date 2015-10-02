from flask import render_template,Response
import json
from app import app

@app.route('/')
@app.route('/index')
def index():
        return render_template('base.html')

@app.route('/update')
def update():
        r = {"data":[[2,3,1,2],[3,4,2,3]]}
        print r
        result = Response(json.dumps(r),mimetype='application/json')
        print result
        return result
