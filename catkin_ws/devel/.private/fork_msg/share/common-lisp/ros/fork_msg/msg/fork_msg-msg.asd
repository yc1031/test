
(cl:in-package :asdf)

(defsystem "fork_msg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "LppCmd" :depends-on ("_package_LppCmd"))
    (:file "_package_LppCmd" :depends-on ("_package"))
  ))