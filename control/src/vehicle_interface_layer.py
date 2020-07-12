import logging
import serial
import json

class VehicleInterfaceLayer():
    LOG = logging.getLogger('VehicleInterfaceLayer')

    def __init__(self, gsl):
        self._gsl = gsl
        self._angle = 0
        self._velocity = 0
        self._distance_front_in_m = 0

    def on(self):
        #self.ser = serial.Serial('COM4', baudrate=9600, timeout=1, parity=serial.PARITY_NONE,bytesize=serial.EIGHTBITS,rtscts=1)
        #self.LOG.info('USB-port: {}'.format(self.ser.name))
        data = dict()
        data["command"] = "vil_adjust_velocity"
        data["value"] = self._velocity
        self._gsl.publishToVehicle(data)
        data["command"] = "vil_adjust_angle"
        data["value"] = self._angle
        self._gsl.publishToVehicle(data)
        self.LOG.info('on')

    def read(self):
        self.LOG.info('Read VIL and SIL updates')
        line = self._gsl.readFromVehicle()
        while((line) != None):
            
            #line = self._gsl.readFromVehicle()
            if len(line) == 0:
                return

            self.LOG.info(line.decode("utf-8"))
            try:
                data = json.loads(line.decode("utf-8"))
                if data['command'] == 'sil_update':
                    self.LOG.info('distance_front_in_m {}'.format(data['distance_front_in_m']))
                    self._distance_front_in_m = data['distance_front_in_m']
                elif data['command'] == 'vil_update_velocity':
                    self.LOG.info('vil velocity {}'.format(data['value']))
                    self._velocity = data['value']
                elif data['command'] == 'vil_update_angle':
                    self.LOG.info('vil angle {}'.format(data['value']))
                    self._angle = data['value']
            except:
                self.LOG.error('problem')
                
            line = self._gsl.readFromVehicle()
