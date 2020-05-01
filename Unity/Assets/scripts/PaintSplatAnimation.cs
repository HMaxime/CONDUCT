using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
using System.Threading.Tasks;

public class PaintSplatAnimation : MonoBehaviour
{
    // Start is called before the first frame update
    Renderer renderer;
    public bool isOriginal = true;
    public int duration = 1000; //temps ou le splat de peinture reste affiché

    void Start()
    {
        renderer  = GetComponent<Renderer>();
        destroyTimer();
    }

    // Update is called once per frame
    void Update()
    {
        //vie de quelques secondes et s'auto détruit en fade
    }

    public async Task destroyTimer()  
    {  
        //fade in
        Color oldCol = renderer.material.color;
        Color newCol = new Color(oldCol.r, oldCol.g, oldCol.b, oldCol.a - 0.01f);
        renderer.material.color = newCol;
        //fin fade In

        await Task.Delay(duration);  
        //fade out
        if (!isOriginal){
           // Object.Destroy(this.gameObject);
        }
    }
}
