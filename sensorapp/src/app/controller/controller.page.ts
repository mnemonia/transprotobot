import { Component, OnInit } from '@angular/core';
import {GpsService} from '../services/sensor/gps.service';
import {MotionService} from '../services/sensor/motion.service';
import {OrientationService} from '../services/sensor/orientation.service';
import {Platform} from "@ionic/angular";
import {TransbotMqttService} from "../services/mqtt/mqtt.service";
import {IMqttMessage} from "ngx-mqtt/src/index";

@Component({
  selector: 'app-controller',
  templateUrl: './controller.page.html',
  styleUrls: ['./controller.page.scss'],
})
export class ControllerPage implements OnInit {
  geo_location_canonical = '';
  altitude = 0;
    altitude_from_mqtt = '';
  time_canonical = '';
    heading = 0;
    speed = 0;
    accuracy = 0;
    x = 0;
    y = 0;
    z = 0;

  constructor(private gpsService: GpsService,
              private motionService: MotionService,
              private orientationService: OrientationService,
              private mgttService: TransbotMqttService,
              private platform: Platform) { }

  ngOnInit() {
      this.mgttService.topic('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude').subscribe(
          (data: IMqttMessage) => {
              this.altitude_from_mqtt = data.payload.toString();
          },
          (err) => {
              console.error(err);
              this.altitude_from_mqtt = 'error';
          },
          () => {
              this.altitude_from_mqtt = 'done';
          }
      )
      /* const success = (position) => {
          const latitude  = position.coords.latitude;
          const longitude = position.coords.longitude;
          console.info('latitude', latitude);
          console.info('longitude', longitude);
      }

      const errorF = () => {
          console.error('Unable to retrieve your location');
      }

      if(!navigator.geolocation) {
          console.warn( 'Geolocation is not supported by your browser' );
      } else {
          console.info( 'Locating…' );
          navigator.geolocation.getCurrentPosition(success, errorF);
      }
      window.addEventListener("devicemotion", (event) => {
          // Process event.acceleration, event.accelerationIncludingGravity,
          // event.rotationRate and event.interval
          console.info('devicemotion', JSON.stringify(event));
      }, true); */
      this.platform.ready().then(() => {
          this.gpsService.gps().subscribe(
              (resp: any) => {
                  console.info('GPS', JSON.stringify(resp));
                  this.geo_location_canonical = 'Lat: ' + resp.coords.latitude + ', Lon: ' + resp.coords.longitude;
                  this.altitude = resp.coords.altitude;
                  this.speed = resp.coords.speed;
                  this.heading = resp.coords.heading;
                  this.accuracy = resp.coords.accuracy;
                  this.mgttService.publishNumber('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', resp.coords.latitude).subscribe(() => {
                      console.info('published latitude');
                  });
                  this.mgttService.publishNumber('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', resp.coords.longitude).subscribe(() => {
                      console.info('published');
                  });
                  this.mgttService.publishNumber('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/altitude', resp.coords.altitude).subscribe(() => {
                      console.info('published');
                  });
                  this.mgttService.publishNumber('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/speed', resp.coords.speed).subscribe(() => {
                      console.info('published');
                  });
                  this.mgttService.publishNumber('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/heading', resp.coords.heading).subscribe(() => {
                      console.info('published');
                  });
                  this.mgttService.publishNumber('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/accuracy', resp.coords.accuracy).subscribe(() => {
                      console.info('published');
                  });
              },
              (err) => console.error(err),
              () => {}
          );
          this.motionService.motion().subscribe(
              (accel) => {
                  console.info('Motion', JSON.stringify(accel));
                  /* accel.x;
                   accel.y;
                   accel.z;
                   accel.timestamp; */
              },
              (err) => console.error(err),
              () => {}
          );
      });

    this.orientationService.orientation().subscribe(
        (heading) => {
          console.info('Heading', JSON.stringify(heading));
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
