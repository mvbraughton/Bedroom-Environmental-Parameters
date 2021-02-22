/**
 *  Humidifier Automation
 *
 *  Copyright 2020 Malcolm Braughton
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */
 import groovy.json.JsonSlurper
import groovy.json.JsonBuilder
definition(
    name: "Humidifier Automation",
    namespace: "mbraughton",
    author: "Malcolm Braughton",
    description: "App will pull humidity readings from Firebase. If humidity readings are less than 60% than the humidifier will turn on. If the humidity is greater than or equal to 60% the humidifier will turn off.",
    category: "My Apps",
    iconUrl: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience.png",
    iconX2Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png",
    iconX3Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png")


preferences {
		// TODO: put inputs here
    section("Turn on or off humidifier.") {
        input "theswitch", "capability.switch", required: true
    }
	
}

def installed() {
	log.debug "Installed with settings: ${settings}"

	initialize()
}

def updated() {
	log.debug "Updated with settings: ${settings}"

	unsubscribe()
	initialize()
}

def initialize() {
	// TODO: subscribe to attributes, devices, locations, etc.
    //sendEventToFirebase()
    //firebaseJsonData()
    log.debug "working"
    timer()
    //data()
    
}
def firebaseJsonData(){
def firebaseJsonData1 = httpGet(uri: "https://humidity-and-temp-52bc0.firebaseio.com/Environmental/switch/Status.json", contentType: 'application/json')
/*
def list = new JsonSlurper().parse(URL("https://humidity-and-temp-52bc0.firebaseio.com/Environmental/data.json"))
log.debug list.Status
def cidval = "" // or whatever default you want
for (rec in list) {
   // if the record has an age, and the age is less than 10, we're done!
   if ( (rec.Temperature) && ( rec.Temperature < ) ) {
         cidval = rec.cid
         break
  }*/






// cidval is either "" or the desired value 

//def data = firebaseJsonData1.toURL().getText()
{resp ->
            		log.debug "resp data: ${resp.data}"
                    
                   // log.debug "result: ${resp.data.result}"
if ("${resp.data}" >= 1)
{
log.debug "Less than 60"
theswitch.on()
}
else{
log.debug "More than 60"
theswitch.off()
}
runIn(60*10, timer)
}
}

def timer()
{

runIn(10, firebaseJsonData)
}
//log.debug data
//return data;



// TODO: implement event handlers
/* Send event data to Google Firebase from http POST */
def sendEventToFirebase(){

	//def serverKey = "AAAA0THZuOY:APA91bHbLPHP8dzf9KciJ8wUDQgVHMovhX4cor76vlwalCTReM_FUkNY-Gh7c_AwC7fxV4RMe7susOiiBcVqbIFxma-suoGYLvZ7myezgde-gbaJNfW5ZMqpvQQJ-OruAlYHj-og36iy"
	//def clientToken = "898484517094"

	//def params = [
	//	uri: "https://fcm.googleapis.com/fcm/send",
	//	headers: [
		//	Authorization: "key=" + serverKey
		//]
        //]
log.debug "before try"
	try {
    log.debug "try block"
		httpGet(uri: "https://humidity-and-temp-52bc0.firebaseio.com/Environmental/data/Status.json")//contentType: 'application/json',) 
        { response ->
        log.debug "Request was successful, $response.status"
        log.debug "after url"
			}
            {resp ->
            		log.debug "resp data: ${resp.data}"
                    log.debug "result: ${resp.data.result}"
                
			log.debug "DEBUG (POST FIREBASE): response contentType: ${resp.    contentType}"
            
           if(resp.data.result == 1){
           		theswitch.on()
          }
            }
		}
	 catch (e) {
		log.debug "something went wrong: $e"
	}
}
