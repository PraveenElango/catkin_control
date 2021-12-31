
(cl:in-package :asdf)

(defsystem "franka_example_controllers-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Floatraj" :depends-on ("_package_Floatraj"))
    (:file "_package_Floatraj" :depends-on ("_package"))
    (:file "JointTorqueComparison" :depends-on ("_package_JointTorqueComparison"))
    (:file "_package_JointTorqueComparison" :depends-on ("_package"))
  ))