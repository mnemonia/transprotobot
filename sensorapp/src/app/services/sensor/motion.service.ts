import { Injectable } from '@angular/core';
import {Observable, of} from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class MotionService {

  constructor() { }

  motion(): Observable<any> {
    return of({x: 1, y: 1, z: 0});
  }
}
