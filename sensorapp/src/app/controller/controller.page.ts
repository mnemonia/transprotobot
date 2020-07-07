import { Component, OnInit } from '@angular/core';
import {GpsService} from '../services/sensor/gps.service';
import {MotionService} from '../services/sensor/motion.service';
import {OrientationService} from '../services/sensor/orientation.service';

@Component({
  selector: 'app-controller',
  templateUrl: './controller.page.html',
  styleUrls: ['./controller.page.scss'],
})
export class ControllerPage implements OnInit {
  geo_location_canonical = '';
  altitude = '';
  time_canonical = '';

  constructor(private gpsService: GpsService,
              private motionService: MotionService,
              private orientationService: OrientationService) { }

  ngOnInit() {
    this.gpsService.gps().subscribe(
        (resp: any) => {
          console.log('GPS', resp);
         // resp.coords.latitude
         // resp.coords.longitude
         // position.coords.altitude
        },
        (err) => console.error(err),
        () => {}
    );
    this.motionService.motion().subscribe(
        (accel) => {
          console.log('Motion', accel);
          /* accel.x;
          accel.y;
          accel.z;
          accel.timestamp; */
        },
        (err) => console.error(err),
        () => {}
    );
    this.orientationService.orientation().subscribe(
        (heading) => {
          console.log('Heading', heading);
          /* heading.magneticHeading;
          heading.trueHeading;
          heading.headingAccuracy;
          heading.timestamp; */
        },
        (err) => console.error(err),
        () => {}
    );
  }

}
