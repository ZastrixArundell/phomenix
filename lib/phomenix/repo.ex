defmodule Phomenix.Repo do
  use Ecto.Repo,
    otp_app: :phomenix,
    adapter: Ecto.Adapters.Postgres
end
