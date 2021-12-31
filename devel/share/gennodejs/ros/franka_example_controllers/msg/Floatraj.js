// Auto-generated. Do not edit!

// (in-package franka_example_controllers.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Floatraj {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.traj = null;
    }
    else {
      if (initObj.hasOwnProperty('traj')) {
        this.traj = initObj.traj
      }
      else {
        this.traj = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Floatraj
    // Check that the constant length array field [traj] has the right length
    if (obj.traj.length !== 3) {
      throw new Error('Unable to serialize array field traj - length must be 3')
    }
    // Serialize message field [traj]
    bufferOffset = _arraySerializer.float64(obj.traj, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Floatraj
    let len;
    let data = new Floatraj(null);
    // Deserialize message field [traj]
    data.traj = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'franka_example_controllers/Floatraj';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a5834651d8cc85e5c144efcfb0dab20e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[3] traj
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Floatraj(null);
    if (msg.traj !== undefined) {
      resolved.traj = msg.traj;
    }
    else {
      resolved.traj = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = Floatraj;
