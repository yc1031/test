;; Auto-generated. Do not edit!


(when (boundp 'fork_msg::LppCmd)
  (if (not (find-package "FORK_MSG"))
    (make-package "FORK_MSG"))
  (shadow 'LppCmd (find-package "FORK_MSG")))
(unless (find-package "FORK_MSG::LPPCMD")
  (make-package "FORK_MSG::LPPCMD"))

(in-package "ROS")
;;//! \htmlinclude LppCmd.msg.html


(defclass fork_msg::LppCmd
  :super ros::object
  :slots (_x _y _yaw _kapp _velocity ))

(defmethod fork_msg::LppCmd
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:yaw __yaw) 0.0)
    ((:kapp __kapp) 0.0)
    ((:velocity __velocity) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _yaw (float __yaw))
   (setq _kapp (float __kapp))
   (setq _velocity (float __velocity))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:kapp
   (&optional __kapp)
   (if __kapp (setq _kapp __kapp)) _kapp)
  (:velocity
   (&optional __velocity)
   (if __velocity (setq _velocity __velocity)) _velocity)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _yaw
    4
    ;; float32 _kapp
    4
    ;; float32 _velocity
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _kapp
       (sys::poke _kapp (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _velocity
       (sys::poke _velocity (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _kapp
     (setq _kapp (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _velocity
     (setq _velocity (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get fork_msg::LppCmd :md5sum-) "a52144db59699080735120a4546b01e6")
(setf (get fork_msg::LppCmd :datatype-) "fork_msg/LppCmd")
(setf (get fork_msg::LppCmd :definition-)
      "float32 x
float32 y
float32 yaw
float32 kapp
float32 velocity
")



(provide :fork_msg/LppCmd "a52144db59699080735120a4546b01e6")


