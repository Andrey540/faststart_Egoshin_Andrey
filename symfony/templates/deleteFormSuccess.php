<div class="container">
  <div class="main_block">
    <div class="header">
      <h1><?= $header ?></h1>
    </div>
    <form action=<?= $action ?> method="post" enctype="multipart/form-data">
  	  <label class="name">File:</label>
	  <input type="text" name="file" value="<?= $fileName ?>"/>	
      <input type="submit" value="Delete" class="button" />
    </form>
  </div>
</div>