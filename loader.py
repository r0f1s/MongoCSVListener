import csv, pymongo, sys, config

def load(filename,delim=None,quote=None):
    DELIM = (delim or config.DELIM)
    QUOTE = (quote or config.QUOTE)
    FILENAME = filename
    PORT = config.PORT
    # connect to the mongodb
    connection = pymongo.Connection(port=PORT)
    # creates a database called listener, if it doesn't exist
    db = connection['listener']

    # creates a collection with the filename
    collection = db[FILENAME.strip('.csv')]

    # inserts the data with header info
    # the "rU" indicates that we're using the
    # "Universal" new line character and that the file is open
    # for reading

    with open(FILENAME, 'rU') as csvfile:
        reader = csv.reader(csvfile,delimiter=DELIM,quotechar=QUOTE)
        for line in reader:
            # headers
            if reader.line_num==1:
                headers=line
            # insert data to the collection
            else:
                collection.insert(dict(zip(headers,line)))
