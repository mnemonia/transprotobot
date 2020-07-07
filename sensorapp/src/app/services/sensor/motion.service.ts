import { Injectable } from '@angular/core';
import { DeviceMotion, DeviceMotionAccelerationData } from '@ionic-native/device-motion/ngx';
import {Observable, timer} from 'rxjs';
import {map} from 'rxjs/operators';

@Injectable({
  providedIn: 'root'
})
export class MotionService {

  constructor(private deviceMotion: DeviceMotion) { }

  motion(): Observable<DeviceMotionAccelerationData> {
    return this.deviceMotion.watchAcceleration();
  }
}
