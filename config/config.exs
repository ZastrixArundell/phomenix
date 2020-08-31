# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.

# General application configuration
use Mix.Config

config :phomenix,
  ecto_repos: [Phomenix.Repo]

# Configures the endpoint
config :phomenix, PhomenixWeb.Endpoint,
  url: [host: "localhost"],
  secret_key_base: "HPjdRPHPv1ya3w40a3LRgLCJU69y1TV49KUjVHSX6GbJNFY6ohxbLNLvvgl7fT48",
  render_errors: [view: PhomenixWeb.ErrorView, accepts: ~w(html json)],
  pubsub_server: Phomenix.PubSub,
  live_view: [signing_salt: "vjCFrYDL"]

# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:request_id]

# Use Jason for JSON parsing in Phoenix
config :phoenix, :json_library, Jason

config :phomenix, PhomenixWeb.Router,
  username: System.get_env("SECRET_USERNAME") || "username",
  password: System.get_env("SECRET_PASSWORD") || "password"

config :phomenix, PhomenixWeb.ControllerSocket,
  secret_auth_key: System.get_env("SECRET_AUTH_KEY") || "SECRET_SAYS_WHAT"

# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env()}.exs"
