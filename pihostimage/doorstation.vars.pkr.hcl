###
# Webrtc settings
#
variable "soundcardid" {
  description = "Id of the soundcard, as listed by `aplay -l`"
  type        = number
  default     = 1
  sensitive   = false
}


variable "gpumem" {
  description = "Size of GPU memory for the RasPi cam"
  type        = number
  default     = 64
  sensitive   = false
}

