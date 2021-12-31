;; Auto-generated. Do not edit!


(when (boundp 'franka_example_controllers::Floatraj)
  (if (not (find-package "FRANKA_EXAMPLE_CONTROLLERS"))
    (make-package "FRANKA_EXAMPLE_CONTROLLERS"))
  (shadow 'Floatraj (find-package "FRANKA_EXAMPLE_CONTROLLERS")))
(unless (find-package "FRANKA_EXAMPLE_CONTROLLERS::FLOATRAJ")
  (make-package "FRANKA_EXAMPLE_CONTROLLERS::FLOATRAJ"))

(in-package "ROS")
;;//! \htmlinclude Floatraj.msg.html


(defclass franka_example_controllers::Floatraj
  :super ros::object
  :slots (_traj ))

(defmethod franka_example_controllers::Floatraj
  (:init
   (&key
    ((:traj __traj) (make-array 3 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _traj __traj)
   self)
  (:traj
   (&optional __traj)
   (if __traj (setq _traj __traj)) _traj)
  (:serialization-length
   ()
   (+
    ;; float64[3] _traj
    (* 8    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[3] _traj
     (dotimes (i 3)
       (sys::poke (elt _traj i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[3] _traj
   (dotimes (i (length _traj))
     (setf (elt _traj i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(setf (get franka_example_controllers::Floatraj :md5sum-) "a5834651d8cc85e5c144efcfb0dab20e")
(setf (get franka_example_controllers::Floatraj :datatype-) "franka_example_controllers/Floatraj")
(setf (get franka_example_controllers::Floatraj :definition-)
      "float64[3] traj

")



(provide :franka_example_controllers/Floatraj "a5834651d8cc85e5c144efcfb0dab20e")


