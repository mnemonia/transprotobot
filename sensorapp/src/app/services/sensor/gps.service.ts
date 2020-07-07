import { Injectable } from '@angular/core';
import {Observable, interval} from 'rxjs';
import { Geolocation, Geoposition } from '@ionic-native/geolocation/ngx';
import {Plugins} from "protractor/built/plugins";
import {fromPromise} from "rxjs/internal/observable/fromPromise";
import {filter} from "rxjs/internal/operators/filter";
import {mergeMap} from "rxjs/internal/operators/mergeMap";

@Injectable({
  providedIn: 'root'
})
export class GpsService {

  constructor(private geolocation: Geolocation) { }

  public gps(): Observable<Geoposition> {
   /* return this.geolocation.watchPosition({
          maximumAge: 3000,
          timeout: 3000,
          enableHighAccuracy: true
        }).pipe(
        filter(res => res.coords !== undefined)
    ); */
      return interval(1000).pipe(
          mergeMap(t => fromPromise(this.geolocation.getCurrentPosition({
              maximumAge: 3000,
              timeout: 3000,
              enableHighAccuracy: true
          }))));
      //return fromPromise(this.geolocation.getCurrentPosition());
  }
}
