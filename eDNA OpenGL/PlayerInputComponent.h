#pragma once
struct PlayerInputComponent
{
    bool isPressingUp{ false };
    bool isPressingDown{ false };
    bool isPressingLeft{ false };
    bool isPressingRight{ false };

    bool isPressingJump{ false };
    bool isPressingAttack{ false };
    bool isPressingBlock{ false };
    bool isPressingDash{ false };

    PlayerInputComponent() = default;
    PlayerInputComponent(const PlayerInputComponent&) = default;
};

