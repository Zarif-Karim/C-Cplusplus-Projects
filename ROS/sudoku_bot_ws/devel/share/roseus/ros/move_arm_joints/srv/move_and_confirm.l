;; Auto-generated. Do not edit!


(when (boundp 'move_arm_joints::move_and_confirm)
  (if (not (find-package "MOVE_ARM_JOINTS"))
    (make-package "MOVE_ARM_JOINTS"))
  (shadow 'move_and_confirm (find-package "MOVE_ARM_JOINTS")))
(unless (find-package "MOVE_ARM_JOINTS::MOVE_AND_CONFIRM")
  (make-package "MOVE_ARM_JOINTS::MOVE_AND_CONFIRM"))
(unless (find-package "MOVE_ARM_JOINTS::MOVE_AND_CONFIRMREQUEST")
  (make-package "MOVE_ARM_JOINTS::MOVE_AND_CONFIRMREQUEST"))
(unless (find-package "MOVE_ARM_JOINTS::MOVE_AND_CONFIRMRESPONSE")
  (make-package "MOVE_ARM_JOINTS::MOVE_AND_CONFIRMRESPONSE"))

(in-package "ROS")





(defclass move_arm_joints::move_and_confirmRequest
  :super ros::object
  :slots (_move ))

(defmethod move_arm_joints::move_and_confirmRequest
  (:init
   (&key
    ((:move __move) 0.0)
    )
   (send-super :init)
   (setq _move (float __move))
   self)
  (:move
   (&optional __move)
   (if __move (setq _move __move)) _move)
  (:serialization-length
   ()
   (+
    ;; float64 _move
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _move
       (sys::poke _move (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _move
     (setq _move (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass move_arm_joints::move_and_confirmResponse
  :super ros::object
  :slots (_confirm ))

(defmethod move_arm_joints::move_and_confirmResponse
  (:init
   (&key
    ((:confirm __confirm) 0.0)
    )
   (send-super :init)
   (setq _confirm (float __confirm))
   self)
  (:confirm
   (&optional __confirm)
   (if __confirm (setq _confirm __confirm)) _confirm)
  (:serialization-length
   ()
   (+
    ;; float64 _confirm
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _confirm
       (sys::poke _confirm (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _confirm
     (setq _confirm (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass move_arm_joints::move_and_confirm
  :super ros::object
  :slots ())

(setf (get move_arm_joints::move_and_confirm :md5sum-) "fee37082f61685d393bcb188db5d451f")
(setf (get move_arm_joints::move_and_confirm :datatype-) "move_arm_joints/move_and_confirm")
(setf (get move_arm_joints::move_and_confirm :request) move_arm_joints::move_and_confirmRequest)
(setf (get move_arm_joints::move_and_confirm :response) move_arm_joints::move_and_confirmResponse)

(defmethod move_arm_joints::move_and_confirmRequest
  (:response () (instance move_arm_joints::move_and_confirmResponse :init)))

(setf (get move_arm_joints::move_and_confirmRequest :md5sum-) "fee37082f61685d393bcb188db5d451f")
(setf (get move_arm_joints::move_and_confirmRequest :datatype-) "move_arm_joints/move_and_confirmRequest")
(setf (get move_arm_joints::move_and_confirmRequest :definition-)
      "float64 move
---
float64 confirm

")

(setf (get move_arm_joints::move_and_confirmResponse :md5sum-) "fee37082f61685d393bcb188db5d451f")
(setf (get move_arm_joints::move_and_confirmResponse :datatype-) "move_arm_joints/move_and_confirmResponse")
(setf (get move_arm_joints::move_and_confirmResponse :definition-)
      "float64 move
---
float64 confirm

")



(provide :move_arm_joints/move_and_confirm "fee37082f61685d393bcb188db5d451f")


