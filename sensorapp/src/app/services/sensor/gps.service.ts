import { Injectable } from '@angular/core';
import {Observable, timer} from 'rxjs';
import { Geolocation } from '@ionic-native/geolocation/ngx';
import {map} from 'rxjs/operators';

@Injectable({
  providedIn: 'root'
})
export class GpsService {

  constructor(private geolocation: Geolocation) { }

  public gps(): Observable<any> {
    return timer(1000).pipe(
        map(t => this.geolocation.getCurrentPosition({
          maximumAge: 3000,
          enableHighAccuracy: true
        }))
    );
  }
}
