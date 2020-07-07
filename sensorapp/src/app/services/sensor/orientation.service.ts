import { Injectable } from '@angular/core';
import {Observable, timer} from 'rxjs';
//import {DeviceOrientation, DeviceOrientationCompassHeading} from '@ionic-native/device-orientation/ngx';

@Injectable({
  providedIn: 'root'
})
export class OrientationService {
  constructor(/* private deviceOrientation: DeviceOrientation */) { }

  orientation(): Observable<any> {
    //return this.deviceOrientation.watchHeading();
    return timer(1000);
  }
}
