import logging
import paho.mqtt.client as mqtt
import json
import numpy as np

class GpsMath():
    LOG = logging.getLogger('GpsMath')

    def earthRadiusInMeters(self, latitudeRadians):
        # latitudeRadians is geodetic, i.e.that reported by GPS.
        # http: // en.wikipedia.org / wiki / Earth_radius
        a = 6378137.0 # equatorial radius in meters
        b = 6356752.3 # polar radius in meters
        cos = np.cos(latitudeRadians)
        sin = np.sin(latitudeRadians)
        t1 = a * a * cos
        t2 = b * b * sin
        t3 = a * cos
        t4 = b * sin
        return np.sqrt((t1 * t1 + t2 * t2) / (t3 * t3 + t4 * t4))

    def geocentricLatitude(self, lat):
        # Convert geodetic latitude 'lat' to a geocentric latitude 'clat'.
        # Geodetic latitude is the latitude as given by GPS.
        # Geocentric latitude is the angle measured from center of Earth between a point and the equator. https: // en.wikipedia.org / wiki / Latitude
        # Geocentric_latitude
        e2 = 0.00669437999014
        clat = np.arctan((1.0 - e2) * np.tan(lat))
        return clat

    def locationToPoint(self, lat, lon, altitude):
        # Convert (lat, lon, elv) to (x, y, z).
        lat = lat * np.pi / 180.0
        lon = lon * np.pi / 180.0
        radius = self.earthRadiusInMeters(lat)
        clat   = self.geocentricLatitude(lat)
        cosLon = np.cos(lon)
        sinLon = np.sin(lon)
        cosLat = np.cos(clat)
        sinLat = np.sin(clat)
        x = radius * cosLon * cosLat
        y = radius * sinLon * cosLat
        z = radius * sinLat

        # We used geocentric latitude to calculate (x,y,z) on the Earth's ellipsoid.
        # Now we use geodetic latitude to calculate normal vector from the surface, to correct for elevation.
        cosGlat = np.cos(lat)
        sinGlat = np.sin(lat)

        nx = cosGlat * cosLon
        ny = cosGlat * sinLon
        nz = sinGlat

        x += altitude * nx
        y += altitude * ny
        z += altitude * nz

        return {"x": x, "y": y, "z":z, "radius":radius, "nx":nx, "ny":ny, "nz":nz}

class GpsService():
    LOG = logging.getLogger('GpsService')
    def __init__(self, gsl):
        self._gsl = gsl
        self._gpsMath = GpsMath()
        self._coords = dict()
        self._coords["lat"] = 0
        self._coords["lon"] = 0
        self._coords["elv"] = 0
        self._latitude = 0
        self._longitude = 0
        self._altitude = 0
        self._heading = 0
        self._cartesianCoords = {"x": 0, "y": 0, "z": 0, "radius": 0, "nx": 0, "ny": 0, "nz": 0 }

    def on(self):
        self.LOG.info('GpsService on ...')
        client = mqtt.Client()

        def on_connect(client, userdata, flags, rc):
            self.LOG.info("Connected with result code " + str(rc))
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/milliseconds')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/fix')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/speed')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/angle')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/altitude')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/satellites')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/compass/heading')

        def on_message(client, userdata, msg):
            self.LOG.info(msg.topic+" "+str(msg.payload))
            if(msg.topic == '/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude'):
                self._latitude = float(msg.payload)
            elif(msg.topic == '/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude'):
                self._longitude = float(msg.payload)
            elif (msg.topic == '/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/altitude'):
                self._altitude = float(msg.payload)
            elif(msg.topic == '/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/compass/heading'):
                self._heading = float(msg.payload)

        client.on_connect = on_connect
        client.on_message = on_message
        self.LOG.info('GpsService connect')
        client.connect("test.mosquitto.org", 1883, 60)
        self.LOG.info('GpsService start')
        client.loop_start()
        self.LOG.info('GpsService on done')

    def read(self):
        self.LOG.info('Read GPS')


class SensorInterfaceLayer():
    LOG = logging.getLogger('PathPlanner')

    def __init__(self, gsl):
        self._gsl = gsl
        self._gpsService = GpsService(gsl)

    def on(self):
        self._gpsService.on()

    def read(self):
        self._gpsService.read()

    def gps(self):
        return self._gpsService


# m = GpsMath()
# ax = [47.032818, 47.032858, 47.032909, 47.033003, 47.033126]
# ay = [9.082638, 9.082606, 9.082588, 9.082527, 9.082423]
# for i in range(5):
    #     res = m.locationToPoint({"lat": ax[i], "lon": ay[i], "elv": 482.1})
    # print("{}".format(json.dumps(res)))
