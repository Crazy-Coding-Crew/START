def downloadData(symbol):
    import urllib2,tempfile
    response = urllib2.urlopen("http://www.google.com/finance/historical?q=%s&output=csv" % symbol)
    data = response.read()
    # delete first line
    data = data[data.index('\n')+1:]
    # replace comma by spaces
    data = data.replace(',',' ')
    tempFile = tempfile.NamedTemporaryFile(prefix="tmpSTART_",suffix=".csv",delete=False)
    tempFile.write(data)
    tempFile.close()    
    return tempFile.name

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser(description="update START DB with historical stock market data from finance.yahoo.com")
    parser.add_argument("symbol",type=str,help="symbol of the stock")

    args = parser.parse_args()
    tempFile = downloadData(args.symbol)
