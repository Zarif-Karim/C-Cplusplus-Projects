// Auto-generated. Do not edit!

// (in-package move_arm_joints.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class move_and_confirmRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.move = null;
    }
    else {
      if (initObj.hasOwnProperty('move')) {
        this.move = initObj.move
      }
      else {
        this.move = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type move_and_confirmRequest
    // Serialize message field [move]
    bufferOffset = _serializer.float64(obj.move, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type move_and_confirmRequest
    let len;
    let data = new move_and_confirmRequest(null);
    // Deserialize message field [move]
    data.move = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'move_arm_joints/move_and_confirmRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ceacabbaabc689d773d1812184680153';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 move
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new move_and_confirmRequest(null);
    if (msg.move !== undefined) {
      resolved.move = msg.move;
    }
    else {
      resolved.move = 0.0
    }

    return resolved;
    }
};

class move_and_confirmResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.confirm = null;
    }
    else {
      if (initObj.hasOwnProperty('confirm')) {
        this.confirm = initObj.confirm
      }
      else {
        this.confirm = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type move_and_confirmResponse
    // Serialize message field [confirm]
    bufferOffset = _serializer.float64(obj.confirm, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type move_and_confirmResponse
    let len;
    let data = new move_and_confirmResponse(null);
    // Deserialize message field [confirm]
    data.confirm = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'move_arm_joints/move_and_confirmResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '96898f38d1c4d4e2071b6fdfb561591f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 confirm
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new move_and_confirmResponse(null);
    if (msg.confirm !== undefined) {
      resolved.confirm = msg.confirm;
    }
    else {
      resolved.confirm = 0.0
    }

    return resolved;
    }
};

module.exports = {
  Request: move_and_confirmRequest,
  Response: move_and_confirmResponse,
  md5sum() { return 'fee37082f61685d393bcb188db5d451f'; },
  datatype() { return 'move_arm_joints/move_and_confirm'; }
};
