import { Injectable } from '@angular/core';
import {Observable} from "rxjs/index";
import {MqttService, IMqttMessage} from "ngx-mqtt";

@Injectable({
  providedIn: 'root'
})
export class TransbotMqttService {

  constructor(
      private _mqttService: MqttService
  ) {
    this._mqttService.connect();
  }

  publishNumber(topic: string, value: number) {
    this._mqttService.unsafePublish(topic, '' + value, {qos: 1, retain: true});
  }

  topic(topicName: string): Observable<IMqttMessage> {
    return this._mqttService.observe(topicName);
  }
}
