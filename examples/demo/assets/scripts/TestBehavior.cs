using WieselEngine;
using System;

public class TestBehavior : MonoBehavior
{

    private TransformComponent transform;
    public float Speed = 0.001f;

    public TestBehavior() {
    }

    public override void OnStart()
    {
        transform = GetComponent<TransformComponent>();
    }

    public override void OnUpdate(float deltaTime)
    {
        //transform.Rotation.Y -= Speed * deltaTime * 150.0f;
    }

}
