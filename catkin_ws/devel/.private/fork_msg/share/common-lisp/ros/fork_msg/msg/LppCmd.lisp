; Auto-generated. Do not edit!


(cl:in-package fork_msg-msg)


;//! \htmlinclude LppCmd.msg.html

(cl:defclass <LppCmd> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (yaw
    :reader yaw
    :initarg :yaw
    :type cl:float
    :initform 0.0)
   (kapp
    :reader kapp
    :initarg :kapp
    :type cl:float
    :initform 0.0)
   (velocity
    :reader velocity
    :initarg :velocity
    :type cl:float
    :initform 0.0))
)

(cl:defclass LppCmd (<LppCmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LppCmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LppCmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fork_msg-msg:<LppCmd> is deprecated: use fork_msg-msg:LppCmd instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <LppCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fork_msg-msg:x-val is deprecated.  Use fork_msg-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <LppCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fork_msg-msg:y-val is deprecated.  Use fork_msg-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <LppCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fork_msg-msg:yaw-val is deprecated.  Use fork_msg-msg:yaw instead.")
  (yaw m))

(cl:ensure-generic-function 'kapp-val :lambda-list '(m))
(cl:defmethod kapp-val ((m <LppCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fork_msg-msg:kapp-val is deprecated.  Use fork_msg-msg:kapp instead.")
  (kapp m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <LppCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fork_msg-msg:velocity-val is deprecated.  Use fork_msg-msg:velocity instead.")
  (velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LppCmd>) ostream)
  "Serializes a message object of type '<LppCmd>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'kapp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LppCmd>) istream)
  "Deserializes a message object of type '<LppCmd>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'kapp) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocity) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LppCmd>)))
  "Returns string type for a message object of type '<LppCmd>"
  "fork_msg/LppCmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LppCmd)))
  "Returns string type for a message object of type 'LppCmd"
  "fork_msg/LppCmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LppCmd>)))
  "Returns md5sum for a message object of type '<LppCmd>"
  "a52144db59699080735120a4546b01e6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LppCmd)))
  "Returns md5sum for a message object of type 'LppCmd"
  "a52144db59699080735120a4546b01e6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LppCmd>)))
  "Returns full string definition for message of type '<LppCmd>"
  (cl:format cl:nil "float32 x~%float32 y~%float32 yaw~%float32 kapp~%float32 velocity~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LppCmd)))
  "Returns full string definition for message of type 'LppCmd"
  (cl:format cl:nil "float32 x~%float32 y~%float32 yaw~%float32 kapp~%float32 velocity~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LppCmd>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LppCmd>))
  "Converts a ROS message object to a list"
  (cl:list 'LppCmd
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':yaw (yaw msg))
    (cl:cons ':kapp (kapp msg))
    (cl:cons ':velocity (velocity msg))
))
