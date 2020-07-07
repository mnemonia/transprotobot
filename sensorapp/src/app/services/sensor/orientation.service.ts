import { Injectable } from '@angular/core';
import {DeviceMotion, DeviceMotionAccelerationData} from '@ionic-native/device-motion/ngx';
import {Observable} from 'rxjs';
import {DeviceOrientation, DeviceOrientationCompassHeading} from '@ionic-native/device-orientation/ngx';

@Injectable({
  providedIn: 'root'
})
export class OrientationService {
  constructor(private deviceOrientation: DeviceOrientation) { }

  orientation(): Observable<DeviceOrientationCompassHeading> {
    return this.deviceOrientation.watchHeading();
  }
}
