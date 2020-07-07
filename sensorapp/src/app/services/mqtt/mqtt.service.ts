import { Injectable } from '@angular/core';
import {Observable} from "rxjs/index";
import {MqttService, IMqttMessage} from "ngx-mqtt";

@Injectable({
  providedIn: 'root'
})
export class TransbotMqttService {

  constructor(
      private _mqttService: MqttService,
  ) {

  }

  publishNumber(topic: string, value: number): Observable<void> {
    return this._mqttService.publish(topic, '' + value);
  }

  topic(topicName: string): Observable<IMqttMessage> {
    return this._mqttService.observe(topicName);
  }
}
