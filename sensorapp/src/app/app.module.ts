import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouteReuseStrategy } from '@angular/router';

import { IonicModule, IonicRouteStrategy } from '@ionic/angular';
import { SplashScreen } from '@ionic-native/splash-screen/ngx';
import { StatusBar } from '@ionic-native/status-bar/ngx';

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';
import {GpsService} from './services/sensor/gps.service';
import {HashLocationStrategy, LocationStrategy} from '@angular/common';
import {MotionService} from './services/sensor/motion.service';
import {Geolocation} from '@ionic-native/geolocation/ngx';
import { DeviceMotion } from '@ionic-native/device-motion/ngx';
import {OrientationService} from './services/sensor/orientation.service';
import {DeviceOrientation} from '@ionic-native/device-orientation/ngx';


@NgModule({
  declarations: [AppComponent],
  entryComponents: [],
  imports: [
    BrowserModule,
    IonicModule.forRoot(),
    AppRoutingModule
  ],
  providers: [
    StatusBar,
    SplashScreen,
    Geolocation,
    GpsService,
    DeviceMotion,
    DeviceOrientation,
      OrientationService,
      MotionService,
    {provide: RouteReuseStrategy, useClass: IonicRouteStrategy},
    {provide: LocationStrategy, useClass: HashLocationStrategy}
  ],
  bootstrap: [AppComponent]
})
export class AppModule {}
