; Auto-generated. Do not edit!


(cl:in-package franka_example_controllers-msg)


;//! \htmlinclude Floatraj.msg.html

(cl:defclass <Floatraj> (roslisp-msg-protocol:ros-message)
  ((traj
    :reader traj
    :initarg :traj
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass Floatraj (<Floatraj>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Floatraj>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Floatraj)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name franka_example_controllers-msg:<Floatraj> is deprecated: use franka_example_controllers-msg:Floatraj instead.")))

(cl:ensure-generic-function 'traj-val :lambda-list '(m))
(cl:defmethod traj-val ((m <Floatraj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader franka_example_controllers-msg:traj-val is deprecated.  Use franka_example_controllers-msg:traj instead.")
  (traj m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Floatraj>) ostream)
  "Serializes a message object of type '<Floatraj>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'traj))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Floatraj>) istream)
  "Deserializes a message object of type '<Floatraj>"
  (cl:setf (cl:slot-value msg 'traj) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'traj)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Floatraj>)))
  "Returns string type for a message object of type '<Floatraj>"
  "franka_example_controllers/Floatraj")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Floatraj)))
  "Returns string type for a message object of type 'Floatraj"
  "franka_example_controllers/Floatraj")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Floatraj>)))
  "Returns md5sum for a message object of type '<Floatraj>"
  "a5834651d8cc85e5c144efcfb0dab20e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Floatraj)))
  "Returns md5sum for a message object of type 'Floatraj"
  "a5834651d8cc85e5c144efcfb0dab20e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Floatraj>)))
  "Returns full string definition for message of type '<Floatraj>"
  (cl:format cl:nil "float64[3] traj~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Floatraj)))
  "Returns full string definition for message of type 'Floatraj"
  (cl:format cl:nil "float64[3] traj~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Floatraj>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'traj) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Floatraj>))
  "Converts a ROS message object to a list"
  (cl:list 'Floatraj
    (cl:cons ':traj (traj msg))
))
