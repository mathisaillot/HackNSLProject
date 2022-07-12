import pandas
import json


#################################################################################################################################################################################
################################################################################ LOAD EXCEL DATA ################################################################################
#################################################################################################################################################################################
def loadSheetName(filename, sheet_name):
    return pandas.read_excel(filename, sheet_name=sheet_name)


def convertSheetToJson(filename, sheet_name):
    df = loadSheetName(filename, sheet_name)
    json_str = df.to_json(orient='records')
    return json.loads(json_str)


#################################################################################################################################################################################
#################################################################################### STATIONS ###################################################################################
#################################################################################################################################################################################
def formatStations(stations):
    for s in stations:
        s['id'] = int(s['id'])
        s['zone'] = int(s['zone'])
        s['row'] = int(s['row'])
        s['col'] = int(s['col'])
        s['concat_id'] = str(int(s['row'])) + str(int(s['col']))
    return stations


#################################################################################################################################################################################
################################################################################## CONNECTIONS ##################################################################################
#################################################################################################################################################################################
def get_connections(station):
    connected_stations = [findS(station), findE(station), findSE(station),
                          findSW(station)]
    return make_connections(station, [s for s in connected_stations if s != False])


def make_connections(station, connected_stations):
    connection_list = []
    for c_s in connected_stations:
        connection_list.append(make_single_connection(station, c_s))
    # return [c for c in connection_list if is_new_connection(c['concat_id'])]
    return connection_list


def make_single_connection(s1, s2):
    s1_id = s1['id']
    s1_concat_id = s1['concat_id']
    s2_id = s2['id']
    s2_concat_id = s2['concat_id']
    d = {
        'concat_id': s1_concat_id + s2_concat_id,
        'stations_id': [s1_id, s2_id],
        'tamise': False}
    d['coord_through'] = get_connection_coord_through(d['concat_id'])
    return d


def get_connection_coord_through(concat_id):
    xa, ya, xb, yb = int(concat_id[0:1]), int(concat_id[1:2]), int(concat_id[2:3]), int(concat_id[3:4])
    if xa == xb:
        return [[xa, y + 0.5 + min(yb, ya)] for y in range(0, abs(yb - ya))] + [[xa, y + min(yb, ya)] for y in
                                                                                range(1, abs(yb - ya))]
    elif ya == yb:
        return [[x + 0.5 + min(xb, xa), ya] for x in range(0, abs(xb - xa))] + [[x + min(xb, xa), ya] for x in
                                                                                range(1, abs(xb - xa))]
    elif ya < yb:
        return [[x + 0.5 + min(xb, xa), x + 0.5 + min(yb, ya)] for x in range(0, abs(xb - xa))] + [
            [x + min(xb, xa), x + min(yb, ya)] for x in range(1, abs(xb - xa))]

    else : 
        return [[-x - 0.5 + max(xb, xa), x + 0.5 + min(yb, ya)] for x in range(0, abs(xb - xa))] + [
            [x + min(xb, xa), -x + max(yb, ya)] for x in range(1, abs(xb - xa))]

def is_new_connection(connection_id):
    other_connection_id = connection_id[2:4] + connection_id[0:2]
    return not len([c for c in CONNECTIONS if c['concat_id'] == other_connection_id])


def findS(station):
    filtered = sorted([s for s in STATIONS if s['col'] == station['col'] and s['row'] > station['row']],
                      key=lambda s: s['row'])
    return filtered[0] if len(filtered) > 0 else False


def findN(station):
    filtered = sorted([s for s in STATIONS if s['col'] == station['col'] and s['row'] < station['row']],
                      key=lambda s: s['row'], reverse=True)
    return filtered[0] if len(filtered) > 0 else False


def findE(station):
    filtered = sorted([s for s in STATIONS if s['row'] == station['row'] and s['col'] > station['col']],
                      key=lambda s: s['col'])
    return filtered[0] if len(filtered) > 0 else False


def findW(station):
    filtered = sorted([s for s in STATIONS if s['row'] == station['row'] and s['col'] < station['col']],
                      key=lambda s: s['col'], reverse=True)
    return filtered[0] if len(filtered) > 0 else False


def findSE(station):
    r, c = station['row'], station['col']
    while r <= 9 and c <= 9:
        r, c = r + 1, c + 1
        filtered = [s for s in STATIONS if s['row'] == r and s['col'] == c]
        if len(filtered) > 0:
            return filtered[0]
    return False


def findSW(station):
    r, c = station['row'], station['col']
    while r <= 9 and c >= 0:
        r, c = r + 1, c - 1
        filtered = [s for s in STATIONS if s['row'] == r and s['col'] == c]
        if len(filtered) > 0:
            return filtered[0]
    return False


def findNE(station):
    r, c = station['row'], station['col']
    while r > 0 and c <= 9:
        r, c = r - 1, c + 1
        filtered = [s for s in STATIONS if s['row'] == r and s['col'] == c]
        if len(filtered) > 0:
            return filtered[0]
    return False


def findNW(station):
    r, c = station['row'], station['col']
    while r > 0 and c > 0:
        r, c = r - 1, c - 1
        filtered = [s for s in STATIONS if s['row'] == r and s['col'] == c]
        if len(filtered) > 0:
            return filtered[0]
    return False


def add_tamise_id_crossing():
    global TAMISE
    i = 0

    for c in CONNECTIONS:
        # id
        c['id'] = i
        i += 1

        # tamise
        inv_id = c['concat_id'][2:4] + c['concat_id'][0:2]
        if c['concat_id'] in TAMISE or inv_id in TAMISE:
            c['tamise'] = True

    for c in CONNECTIONS:
        intersect = []
        for con in CONNECTIONS:
            c_inter = [con['id'] for point in con['coord_through'] if
                       point in c['coord_through'] and con['id'] != c['id']]
            if len(c_inter):
                intersect = intersect + c_inter
        c['crossing'] = intersect

    for c in CONNECTIONS:
        del c['coord_through']


# def add_crossing_connections():
#     global CONNECTIONS
#     for c in CONNECTIONS:

#################################################################################################################################################################################
#################################################################################### PROCESS ####################################################################################
#################################################################################################################################################################################
def process(filename):
    global STATIONS, CONNECTIONS
    main_json_data = {}

    # No need processing
    main_json_data['version'] = 'London'
    main_json_data['station_types'] = ['square', 'circle', 'triangle', 'hexagone', 'joker']

    # Stations
    STATIONS = convertSheetToJson(filename, 'stations')
    STATIONS = formatStations(STATIONS)
    main_json_data['stations'] = STATIONS

    # Depart Stations
    main_json_data['stations_depart'] = convertSheetToJson(filename, 'stations_depart')

    # Connections
    for s in STATIONS:
        CONNECTIONS = CONNECTIONS + get_connections(s)
    add_tamise_id_crossing()
    main_json_data['connections'] = CONNECTIONS

    # Write JSON
    with open('../NSLdata.json', 'w', encoding='utf-8') as f:
        json.dump(main_json_data, f, indent=4)


#################################################################################################################################################################################
###################################################################################### RUN ######################################################################################
#################################################################################################################################################################################
filename = 'HackNSL BDD.xlsx'

STATIONS = []
CONNECTIONS = []
TAMISE = ['3050', '1141', '3242', '2363', '5464', '4575', '3666', '3757', '4878', '3969', '4244', '5254', '5457',
          '3041', '2042', '4466', '4567', '3557', '3669', '4132', '5234', '6354', '6437', '5748']
process(filename)
